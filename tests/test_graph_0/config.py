import pbs.classes.Executable

e = pbs.classes.Executable.Executable("test_graph_0", self)

e.require("graph")

e.make()

