# -*- coding: utf8 -*-
#
import os
import argparse
import logging

class Main(object):
	def __init__(self):
		self.scriptPath = os.path.split(os.path.realpath(__file__))[0]
		self.rootPath = os.path.dirname(os.path.dirname(os.path.dirname(self.scriptPath)))
		self.androidScPath = os.path.join(self.rootPath, 'android-6.0.1_r11')
		self.androidexPath = os.path.join(self.rootPath, 'androidex')
		
		self.softLinkList = (
			(self.scriptPath,
				os.path.join(self.androidScPath, 'packages', 'experimental', 'HelloAndroid')
				),
			)

	def Init(self):
		for item in self.softLinkList:
			src = item[0]
			dst = item[1]
			if os.path.exists(dst):
				logging.debug('文件已存在，无需创建软链：\n%s' % dst)
				continue
			cmdString = 'ln -s %s %s' % (src, dst)
			logging.debug('[exec:] %s' % cmdString)
			os.system(cmdString)


	def Clear(self):
		for item in self.softLinkList:
			src = item[0]
			dst = item[1]
			if not os.path.exists(dst):
				logging.debug('文件不存在，无需删除软链：\n%s' % dst)
				continue
			cmdString = 'rm -f %s' % (dst)
			logging.debug('[exec:] %s' % cmdString)
			os.system(cmdString)


if __name__ == '__main__':
	loggingFormat	=	'%(asctime)s %(lineno)04d %(levelname)-8s %(message)s'
	logging.basicConfig(level=logging.DEBUG,	format=loggingFormat,	datefmt='%H:%M',	)
	argParser = argparse.ArgumentParser()
	argParser.add_argument('-i', '--init', action='store_true', default=True)
	argParser.add_argument('-c', '--clear', action='store_true', default=False)
	args = argParser.parse_args()

	mainProc = Main()
	if args.clear:
		mainProc.Clear()
	elif args.init:
		mainProc.Init()
	else:
		logging.debug("Failed to parse param")
		print args
