import numpy as np
import nmslib
import unittest
import random

class TestItterable(unittest.TestCase):

    def test(self):
        X = [
            ' '.join(random.choice(['1','0']) for _ in range(10)) for _ in range(6)
            ]
        
        def X_itterator():
            for x in X:
                yield x
        
        string_index = nmslib.init(method='hnsw', space='bit_jaccard', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        string_index.addDataPointBatch(X_itterator())
        string_index.createIndex({'post': 2}, print_progress=False)

    
        for i in range(len(X)):
            ids, dists = string_index.knnQuery(X[i], k=5)
            
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(string_index.getDistanceToObj(X[i] ,X[id]), dist, places=6)

    def test_compare(self):
        """ 
        Note: this fails with numbers smaller than 10000
        I think this is because the distance might be the same for two objects

        With this high number we make it more likely that the distance is different
        and so the knn query will return same results for both indices
        """
        X = list(set(
            ' '.join(random.choice(['1','0']) for _ in range(10000)) for _ in range(100)
            ))
        
        def X_itterator():
            for x in X:
                yield x
        
        string_index1 = nmslib.init(method='hnsw', space='bit_jaccard', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        string_index1.addDataPointBatch(X_itterator())
        string_index1.createIndex({'post': 2}, print_progress=False)

        string_index2 = nmslib.init(method='hnsw', space='bit_jaccard', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        string_index2.addDataPointBatch(X)
        string_index2.createIndex({'post': 2}, print_progress=False)



        for i in range(len(X)):
            k = 5
            ids1, dists1 = string_index1.knnQuery(X[i], k=k)
            ids2, dists2 = string_index2.knnQuery(X[i], k=k)


            for u in range(k):
                self.assertEqual(ids1[u], ids2[u])
                self.assertAlmostEqual(dists1[u], dists2[u], places=6)

if __name__ == '__main__':
    unittest.main()