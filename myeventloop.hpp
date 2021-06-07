# ifndef MY_EVENT_LOOP
# define MY_EVENT_LOOP


#include <mutex>
#include <functional>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace boost { namespace python { namespace myeventloop {


class MyEventLoop
{
public:
    virtual ~MyEventLoop() {};
    virtual void call_soon(std::function<void(MyEventLoop&)> f) = 0;
    virtual void call_when_fd_ready(
        int fd, std::function<void(MyEventLoop&)> f) = 0;
};

class EventLoop: public MyEventLoop
{
private:
    boost::asio::io_context::strand _strand;
    std::shared_ptr<std::mutex> _descriptors_mutex;
    std::unordered_map<int, std::shared_ptr<boost::asio::posix::stream_descriptor>> _descriptors;

    static void _release_descriptor_and_callback(
        int fd, 
        std::function<void(MyEventLoop&)> f,
        EventLoop& loop)
    {
        const std::lock_guard<std::mutex> lock(*(loop._descriptors_mutex));
        loop._remove_descriptor(fd);
        loop.call_soon(f);
    }

    void _add_descriptor(int fd)
    {
        if (_descriptors.find(fd) == _descriptors.end())
        {
            _descriptors.insert({fd,
                std::make_shared<boost::asio::posix::stream_descriptor>(_strand.context(), fd)
            });
        }
    }
    
    void _remove_descriptor(int fd)
    {
        auto iter = _descriptors.find(fd);
        if (iter != _descriptors.end())
        {
            iter->second->release();
        }
        _descriptors.erase(iter);
    }

public:
    EventLoop(boost::asio::io_context& ctx):
        _strand(ctx),
        _descriptors_mutex{new std::mutex}
    {
    }

    ~EventLoop() 
    {
    }

    void call_soon(std::function<void(MyEventLoop&)> f)
    {
        _strand.post(boost::bind(f, boost::ref(*this)));
        return;
    }

    void call_when_fd_ready(int fd, std::function<void(MyEventLoop&)> f)
    {
        const std::lock_guard<std::mutex> lock(*_descriptors_mutex);
        _add_descriptor(fd);

        _descriptors.find(fd)->second->async_wait(boost::asio::posix::descriptor::wait_type::wait_read,
            boost::asio::bind_executor(_strand, boost::bind(
                _release_descriptor_and_callback, fd, f, boost::ref(*this))));
        return;
    }

    void run() 
    {
        _strand.context().run();
    }
};


}}}


# endif
