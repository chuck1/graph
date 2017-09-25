#import pbs.classes.Dynamic
import os
import pbs2

self.execfile(os.path.join(__dir__, '../logs/config.py'))

l = pbs2.Library(self, 'graph', __file__)

#l = pbs.classes.Static.Static("graph", self)

#l.make()

#self.include("tests")

l.l_defines.append('GR_GRAPH_HPP_IN_LOGGER_MODE=logs::mode::RUN_TIME')
l.l_defines.append('GR_GRAPH_HPP_IN_LOGGER_LEVEL=1')

l.l_defines.append('GR_ALGO_FOR_EACH_LEAF_FOREACHLEAF_HPP_IN_LOGGER_MODE=logs::mode::RUN_TIME')
l.l_defines.append('GR_ALGO_FOR_EACH_LEAF_FOREACHLEAF_HPP_IN_LOGGER_LEVEL=1')

l.doc_out_dir = "/media/sf_P_DRIVE/html/graph"

l.add_dep('logs')

#l.args.append('--no-pie')
#l.args.append('-fPIC')

self.parts.append(l)

self.execfile(os.path.join(__dir__, "tests/config.py"))

