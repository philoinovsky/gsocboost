#include <boost/python.hpp>
#include <boost/python/myeventloop.hpp>
using namespace boost::python;

void event_loop_call_soon_aux(
    boost::python::myeventloop::EventLoop& self, boost::python::object f)
{
    self.call_soon(f);
}

void event_loop_call_when_fd_ready_aux(
    boost::python::myeventloop::EventLoop& self, int fd, boost::python::object f)
{
    self.call_when_fd_ready(fd, f);
}


BOOST_PYTHON_MODULE(eventloop_ext)
{
    class_<boost::asio::io_context>("io_context");

    class_<myeventloop::MyEventLoop, boost::noncopyable>("myeventloop", no_init);

    class_<myeventloop::EventLoop, bases<myeventloop::MyEventLoop>>("eventloop", init<boost::asio::io_context&>())
        .def("call_soon", &event_loop_call_soon_aux, arg("f"))
        .def("call_when_fd_ready", &event_loop_call_when_fd_ready_aux, (arg("fd"), arg("f")))
        .def("run", &myeventloop::EventLoop::run);
}
