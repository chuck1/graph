import pbs

e = pbs.Executable(self, "test_lp", __file__)

e.add_dep("graph")

self.parts.append(e)

