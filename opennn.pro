###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.intelnics.com/opennn                                                                      #
#                                                                                                 #
#   O P E N N N   P R O J E C T                                                                   #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Intelnics - The artificial intelligence company                                               #
#   robertolopez@intelnics.com                                                                    #
#                                                                                                 #
###################################################################################################

# CONFIGURATION

TEMPLATE = subdirs

CONFIG += ordered

CONFIG(release, debug|release) {
DEFINES += NDEBUG
}

SUBDIRS += \
    tinyxml2 \
    source

SUBDIRS += tests
SUBDIRS += examples
