#!/bin/sh

./bin/dummy_test_case | tee ../log/dummy_test_case_$(date '+%Y-%m-%d_%H-%M-%S'.log)
