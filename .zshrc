BOOST_PATH="${HOME}/boost"
PY_VER="3.9"
PY_VER1="39"
export INCLUDE="${BOOST_PATH}"
export LIBRARY_PATH="${BOOST_PATH}/stage/lib"
export LD_LIBRARY_PATH="${BOOST_PATH}/stage/lib"

compile () {
	g++ "${1}" -I/usr/include/python${PY_VER} -I${BOOST_PATH} -o k -L${BOOST_PATH}/stage/lib -lboost_thread $(/usr/bin/python${PY_VER}-config --ldflags --embed) -fno-lto -lboost_python${PY_VER1} -lboost_system
}


cd ${BOOST_PATH}/libs/python
