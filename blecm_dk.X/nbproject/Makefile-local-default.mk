#
# Generated Makefile - do not edit!
#
#
# This file contains information about the location of compilers and other tools.
# If you commmit this file into your revision control server, you will be able to 
# to checkout the project and build it from the command line with make. However,
# if more than one person works on the same project, then this file might show
# conflicts since different users are bound to have compilers in different places.
# In that case you might choose to not commit this file and let MPLAB X recreate this file
# for each user. The disadvantage of not commiting this file is that you must run MPLAB X at
# least once so the file gets created and the project can be built. Finally, you can also
# avoid using this file at all if you are only building from the command line with make.
# You can invoke make with the values of the macros:
# $ makeMP_CC="/opt/microchip/mplabc30/v3.30c/bin/pic30-gcc" ...  
#
<<<<<<< HEAD
PATH_TO_IDE_BIN=/opt/microchip/mplabx/v3.45/mplab_ide/platform/../mplab_ide/modules/../../bin/
# Adding MPLAB X bin directory to path.
PATH:=/opt/microchip/mplabx/v3.45/mplab_ide/platform/../mplab_ide/modules/../../bin/:$(PATH)
# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH="/opt/microchip/mplabx/v3.45/sys/java/jre1.8.0_91/bin/"
=======
PATH_TO_IDE_BIN=/sdd/opt/microchip/mplabx/v3.45/mplab_ide/platform/../mplab_ide/modules/../../bin/
# Adding MPLAB X bin directory to path.
PATH:=/sdd/opt/microchip/mplabx/v3.45/mplab_ide/platform/../mplab_ide/modules/../../bin/:$(PATH)
# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH="/sdd/opt/microchip/mplabx/v3.45/sys/java/jre1.8.0_91/bin/"
>>>>>>> 32198c5428f179fd031a19d0db2f53a27b90ef51
OS_CURRENT="$(shell uname -s)"
MP_CC="/sdd/opt/microchip/xc16/v1.26/bin/xc16-gcc"
# MP_CPPC is not defined
# MP_BC is not defined
<<<<<<< HEAD
MP_AS="/opt/microchip/xc16/v1.26/bin/xc16-as"
MP_LD="/opt/microchip/xc16/v1.26/bin/xc16-ld"
MP_AR="/opt/microchip/xc16/v1.26/bin/xc16-ar"
DEP_GEN=${MP_JAVA_PATH}java -jar "/opt/microchip/mplabx/v3.45/mplab_ide/platform/../mplab_ide/modules/../../bin/extractobjectdependencies.jar"
MP_CC_DIR="/opt/microchip/xc16/v1.26/bin"
=======
MP_AS="/sdd/opt/microchip/xc16/v1.26/bin/xc16-as"
MP_LD="/sdd/opt/microchip/xc16/v1.26/bin/xc16-ld"
MP_AR="/sdd/opt/microchip/xc16/v1.26/bin/xc16-ar"
DEP_GEN=${MP_JAVA_PATH}java -jar "/sdd/opt/microchip/mplabx/v3.45/mplab_ide/platform/../mplab_ide/modules/../../bin/extractobjectdependencies.jar"
MP_CC_DIR="/sdd/opt/microchip/xc16/v1.26/bin"
>>>>>>> 32198c5428f179fd031a19d0db2f53a27b90ef51
# MP_CPPC_DIR is not defined
# MP_BC_DIR is not defined
MP_AS_DIR="/sdd/opt/microchip/xc16/v1.26/bin"
MP_LD_DIR="/sdd/opt/microchip/xc16/v1.26/bin"
MP_AR_DIR="/sdd/opt/microchip/xc16/v1.26/bin"
# MP_BC_DIR is not defined
