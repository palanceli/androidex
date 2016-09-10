# -*- coding: utf8 -*-
#
import 	os
import 	logging
import	sys
import	optparse
import	datetime
import	time
import	argparse


class FolderSize(object):
	def __init__(self, folder):
		self.folder = folder

	def MainProc(self):
		logging.debug('MainProc')

if __name__ == '__main__':
	loggingFormat	=	'%(asctime)s %(lineno)04d %(levelname)-8s %(message)s'
	logging.basicConfig(level=logging.DEBUG,	format=loggingFormat,	datefmt='%H:%M',	)
	parser = argparse.ArgumentParser(description='通过adb shell 计算指定文件夹大小.')
	parser.add_argument('folder', metavar='folder', nargs=1, help='要计算的文件夹')
	args = parser.parse_args()

	folderSize = FolderSize(args.folder)
	folderSize.MainProc()
