#
# Developed by:  Mario Emmenlauer (mario@emmenlauer.de)
#                Balanstrasse 43, 81669 Munich
#                http://www.biodataanalysis.de/
#
# With contributions by:
#
#
# Copyright (c) 2014-2018, BioDataAnalysis GmbH
# All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are not permitted. All information contained herein
# is, and remains the property of BioDataAnalysis GmbH.
# Dissemination of this information or reproduction of this material
# is strictly forbidden unless prior written permission is obtained
# from BioDataAnalysis GmbH.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#

default:	all
all:	../bin/task01 ../bin/task02 ../bin/task03


../bin/task%:	task%.cc Makefile
	mkdir -p ../bin/ && \
	g++ -std=c++11 -I$(HOME)/usr/vigra-$(HOSTTYPE)/include -o $@ $<

run:	all
	../bin/task01 && \
	../bin/task02 && \
	../bin/task03

