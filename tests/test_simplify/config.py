import pbs

e = pbs.Executable(self, "test_simplify", __file__)

e.add_dep("graph")

#e.args.append('--no-pie')
#e.args.append('-fPIC')
e.args.args.append('-lglpk')
e.args.args.append('-lz')

self.parts.append(e)

