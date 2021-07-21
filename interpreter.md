## O. preludes
- one interpreter can have multiple threads in it
## I. create and use an interpreter
1. option A
```
// create an interpreter and the 1st thread, and returns this thread
PyThreadState* ts = PyThreadState_Swap(Py_NewInterpreter());
```
2. option B
```
// create an interpreter
PyInterpreterState* interp = PyInterpreterState_New();
// create a thread in it
PyThreadState* ts = PyThreadState_Swap(PyThreadState_New(interp));
```
#### Note
- `PyThreadState_Swap` = `PyEval_SaveThread` + `PyEval_RestoreThread`
- `PyThreadState_Swap` can be used to switch between threads/interpreters
- problem: `PyThreadState_Swap` returns the thread state switched in, not the one switched out
## II. destroy interpreter
```
Py_EndInterpreter(ts);
PyThreadState_Swap(main_ts);
```
#### Note
- PyObject refcnt __*won't*__ prevent interpreter from being destroyed
## III. different sub-interpreters share the same GIL
from python doc: Threads belonging to different interpreters initially share nothing, except process state like available memory, open file descriptors and such. The global interpreter lock is also shared by all threads, regardless of to which interpreter they belong. https://docs.python.org/3/c-api/init.html#c.PyInterpreterState
## IV. get the sub-interpreter who owns the PyObject and detect its validity
- __*didn't find a way to get the corresponding sub-interpreter*__
- `PyInterpreterState_GetID(interp)` returns -1 when interp is not valid
