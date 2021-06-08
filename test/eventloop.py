import eventloop_ext as eventloop

def f(loop):
    print("hello world")

if __name__ == "__main__":
    loop = eventloop.eventloop(ctx)
    loop.call_soon(f)
    loop.run()
