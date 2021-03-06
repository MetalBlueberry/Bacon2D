include(doc/doc.pri)

TEMPLATE = subdirs

CONFIG += ordered   # This tells Qt to compile the following SUBDIRS in order

SUBDIRS += src \
    tests \
    examples

PROJECT_NAME = bacon2d
PROJECT_VERSION = 0.90.7.1

DISTNAME = $${PROJECT_NAME}-$${PROJECT_VERSION}
dist.commands = "cd ../ && ./git-archive-all.sh --prefix $${DISTNAME}/ $${DISTNAME}.tar && bzip2 $${DISTNAME}.tar && cd -"
QMAKE_EXTRA_TARGETS += dist
