#!/usr/bin/python

"""
	This library should be used to interface with the STM VL53L1X
"""
import time
import smbus

class VL53L1X(object):
	"""docstring for VL53L1X"""
	def __init__(self, bus):
		super(VL53L1X, self).__init__()
		self.bus = bus
