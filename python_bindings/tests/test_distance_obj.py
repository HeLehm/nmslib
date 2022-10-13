import numpy as np
import nmslib
import unittest
import faulthandler; faulthandler.enable()
import random

class TestOuterDistance(unittest.TestCase):

    def test_outer_distance(self):
        X = [
            ' '.join(random.choice(['1','0']) for _ in range(10)) for _ in range(6)
            ]


        string_index = nmslib.init(method='hnsw', space='bit_jaccard', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        string_index.addDataPointBatch(X)
        string_index.createIndex({'post': 2}, print_progress=False)

        for i in range(len(X)):
            ids, dists = string_index.knnQuery(X[i], k=5)
            
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(string_index.getDistanceToObj(X[i] ,X[id]), dist, places=6)
    
    def test_lft_rgt_dist(self):
        X = [
            ' '.join(random.choice(['1','0']) for _ in range(10)) for _ in range(6)
        ]

        string_index = nmslib.init(method='hnsw', space='bit_jaccard', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        string_index.addDataPointBatch(X)
        string_index.createIndex({'post': 2}, print_progress=False)

        for i in range(len(X)):
            ids, dists = string_index.knnQuery(X[i], k=5)
            
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(string_index.getDistanceToObjLft(X[i] ,id), dist, places=6)

        for i in range(len(X)):
            ids, dists = string_index.knnQuery(X[i], k=5)
            
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(string_index.getDistanceToObjRgt(i ,X[id]), dist, places=6)
        



if __name__ == '__main__':
    unittest.main()
        

