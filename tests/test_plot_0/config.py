import pbs

e = pbs.Executable(self, "test_plot_0", __file__)

e.add_dep("graph")

self.parts.append(e)

