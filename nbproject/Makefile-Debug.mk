#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Random_Kill-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Display.o \
	${OBJECTDIR}/src/Entity/Entity.o \
	${OBJECTDIR}/src/Entity/Player.o \
	${OBJECTDIR}/src/IO.o \
	${OBJECTDIR}/src/Input.o \
	${OBJECTDIR}/src/Map.o \
	${OBJECTDIR}/src/RK.o \
	${OBJECTDIR}/src/Sound.o \
	${OBJECTDIR}/src/Stats.o \
	${OBJECTDIR}/src/View/GameView.o \
	${OBJECTDIR}/src/View/MenuView.o \
	${OBJECTDIR}/src/View/View.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/random_kill

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/random_kill: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/random_kill ${OBJECTFILES} ${LDLIBSOPTIONS} -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

${OBJECTDIR}/src/Display.o: src/Display.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Display.o src/Display.cpp

${OBJECTDIR}/src/Entity/Entity.o: src/Entity/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Entity/Entity.o src/Entity/Entity.cpp

${OBJECTDIR}/src/Entity/Player.o: src/Entity/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Entity/Player.o src/Entity/Player.cpp

${OBJECTDIR}/src/IO.o: src/IO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IO.o src/IO.cpp

${OBJECTDIR}/src/Input.o: src/Input.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Input.o src/Input.cpp

${OBJECTDIR}/src/Map.o: src/Map.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Map.o src/Map.cpp

${OBJECTDIR}/src/RK.o: src/RK.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RK.o src/RK.cpp

${OBJECTDIR}/src/Sound.o: src/Sound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Sound.o src/Sound.cpp

${OBJECTDIR}/src/Stats.o: src/Stats.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Stats.o src/Stats.cpp

${OBJECTDIR}/src/View/GameView.o: src/View/GameView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/View
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/View/GameView.o src/View/GameView.cpp

${OBJECTDIR}/src/View/MenuView.o: src/View/MenuView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/View
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/View/MenuView.o src/View/MenuView.cpp

${OBJECTDIR}/src/View/View.o: src/View/View.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/View
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/View/View.o src/View/View.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/random_kill

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
