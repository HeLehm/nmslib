import numpy as np
import nmslib
import unittest
import random


class TestSpace(unittest.TestCase):
    def test_desc(self):
        index = nmslib.init(
            method='hnsw',
            space='mylingua',
            space_params={
                'wordWeight': 0.5,
                'wordLength': 3,
            },
            data_type=nmslib.DataType.OBJECT_AS_STRING,
            dtype=nmslib.DistType.FLOAT,
        )
        desc = index.getSpaceDesc()
        self.assertEqual(desc, "MyLingua Score, wordWeight=0.5, wordLength=3")
        print(desc)

    def test_space(self):
        index = nmslib.init(
            method='hnsw',
            space='mylingua',
            space_params={
                'wordWeight': 0.8,
                'wordLength': 3,
            },
            data_type=nmslib.DataType.OBJECT_AS_STRING,
            dtype=nmslib.DistType.FLOAT,
        )
        full_word_length = 3 * 32
        full_length = full_word_length * 2

        user_fake = ''.join('1' * full_word_length) + ''.join('0' * full_word_length)
        content_fake = ''.join('1' * full_word_length) + ''.join('1' * full_word_length)

        user_fake = ' '.join(user_fake)
        content_fake = ' '.join(content_fake)

        #TODO actulary write unittest
        dist = index.getDistanceToObj(user_fake, content_fake)
        print(dist)


if __name__ == '__main__':
    unittest.main()