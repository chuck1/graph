
import pbs.classes.Static

l = pbs.classes.Static.Static("graph", self)

l.inc_dirs.append("/home/crymal/backedup/git/hvac_cpp/graph/include")
l.inc_dirs.append("/home/crymal/backedup/git/hvac_cpp/graph/build/static/process/include")

l.libs = ["-l/home/crymal/backedup/git/hvac_cpp/graph/build/static/libgraph.a"]

