import numpy as np
import nmslib
import unittest
import faulthandler; faulthandler.enable()
import random

class TestOuterDistance(unittest.TestCase):

    def tessst_inner_distance(self):
        # Test that inner distance is correctly computed.
        # This is a regression test for a bug that caused inner distance to be computed incorrectly.
        # See
        X_input = np.random.rand(10,3).astype(np.float32)
        
        float_index = nmslib.init(method='hnsw', space='cosinesimil', dtype=nmslib.DistType.FLOAT)
        float_index.addDataPointBatch(X_input)
        float_index.createIndex({'post': 2}, print_progress=False)

        for i in range(10):
            ids, dists = float_index.knnQuery(X_input[i], k=5)
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(float_index.getDistance(i,id) , dist, places=6)

        
        self.assertTrue(True)

    def tesssst_inner_distance_string(self):

        X = [
            ' '.join(random.choice(['1','0']) for _ in range(10))
        ]

        string_index = nmslib.init(method='hnsw', space='bit_jaccard', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        string_index.addDataPointBatch(X)
        string_index.createIndex({'post': 2}, print_progress=False)
        print("Done creatimh jaccard index")

        for i in range(10):
            ids, dists = string_index.knnQuery(X[i], k=5)
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(string_index.getDistanceToObj(i,[X[id]]) , dist, places=6)

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
        

