import pbs

e = pbs.Executable(self, "test", __file__)

e.add_dep("graph")

#e.args.append('--no-pie')
#e.args.append('-fPIC')
e.args.args.append('-lglpk')

self.parts.append(e)

