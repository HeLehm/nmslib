import unittest
import nmslib
import numpy as np

class TestFloatEncoding(unittest.TestCase):
    def test_float_encoding(self):
        # Test that float32 are encoded correctly.
        # This is a regression test for a bug that caused float32 to be encoded as float64.
        # See
        X = np.random.rand(100).astype(np.float32)
        X_input = [' '.join(nmslib.float_to_bits(x)) for x in X.flatten()]
        float_index = nmslib.init(method='hnsw', space='test_encode_float', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.FLOAT)
        float_index.addDataPointBatch(X_input)
        float_index.createIndex({'post': 2}, print_progress=False)

        for i,x in enumerate(X_input):
            _, dist =float_index.knnQuery(x, k=1)
            self.assertTrue(dist[0] == X[i])

class TestIntEncoding(unittest.TestCase):
    def test_int_encoding(self):
        # Test that int32  are encoded correctly.
        # This is a regression test for a bug that caused int32 to be encoded as int64.
        # See
        X = np.random.randint(0, 100, 100, dtype=np.uint32)
        X_input = [' '.join(nmslib.uint32_to_bits(x)) for x in X.flatten()]
        
        int_index = nmslib.init(method='hnsw', space='test_encode_uint', data_type=nmslib.DataType.OBJECT_AS_STRING, dtype=nmslib.DistType.INT)
        int_index.addDataPointBatch(X_input)
        int_index.createIndex({'post': 2}, print_progress=False)

        for i,x in enumerate(X_input):
            _, dist =int_index.knnQuery(x, k=1)
            self.assertTrue(dist[0] == X[i])


if __name__ == '__main__':
    unittest.main()
    




