import numpy as np
import nmslib
import unittest
import random


class TestItterable(unittest.TestCase):
    def test(self):

        width = 72
        height = 72
        channels = 4

        np.random.seed(42)

        X = [
            np.random.random(width * height * channels).reshape(width,height,channels) for _ in range(10)
        ]

        
        X_input = [x.flatten() for x in X]

        index = nmslib.init(method='hnsw', space='alpha_img_eucl', dtype=nmslib.DistType.FLOAT)
        index.addDataPointBatch(X_input)
        index.createIndex({'post': 2}, print_progress=False)

 
        for i,x in enumerate(X_input):
            ids, dists = index.knnQuery(x, k=5)
            for id, dist in zip(ids, dists):
                self.assertAlmostEqual(self.python_distance(X[i], X[id]), dist, places=1)

        


        self.assertEqual(1, 1)
        pass

    def python_distance(self, x, y):
        res = 0
        for i in range(x.shape[0]):
            for j in range(x.shape[1]):
                for k in range(x.shape[2] - 1):
                    dist = x[i,j,k] - y[i,j,k]
                    dist *= x[i,j,3] * y[i,j,3] #aplha
                    res += dist * dist
        return res


if __name__ == '__main__':
    unittest.main()