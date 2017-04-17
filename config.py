#import pbs.classes.Dynamic
import os
import pbs2

l = pbs2.Library(self, 'graph', __file__)

#l = pbs.classes.Static.Static("graph", self)

#l.make()

#self.include("tests")

l.doc_out_dir = "/media/sf_P_DRIVE/html/graph"

self.parts.append(l)

self.execfile(os.path.join(__dir__, "tests/config.py"))

