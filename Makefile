#******************************
# 		CONFIGURATIONS
#******************************

ROOT_DIR := $(pwd)
APP_DIR := app
BUILD_DIR := *build
TEST_DIR := app

#******************************
#	        CLIENT
#******************************

CLIENT_DIR := $(APP_DIR)/client-platform
CLIENT_BUILD_DIR := client-platform-build
CLIENT_TEST_DIR := $(CLIENT_DIR)/test

# Creates directory and runs cmake to build the project
build-client:
	@echo "[INFO] Building 'client'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(CLIENT_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(CLIENT_TEST_DIR) ; \
	mkdir -p $(CLIENT_BUILD_DIR) ; \
	cd $(CLIENT_BUILD_DIR) && cmake ../$(CLIENT_DIR)

# Compiles the C++ code for the project
compile-client:
	@echo "[INFO] Compiling 'client'" ; \
	$(MAKE) -C $(CLIENT_BUILD_DIR) --silent

# Runs the test-suite
test-client:
	@echo "[INFO] client tests commencing..." ; \
	cd $(CLIENT_BUILD_DIR) && bin/tests-client


#******************************
#	   CORE GAME ENGINE
#******************************

CORE_GAME_ENGINE_DIR := $(APP_DIR)/core-game-engine
CORE_GAME_ENGINE_BUILD_DIR := core-game-engine-build
CORE_GAME_ENGINE_TEST_DIR := $(CORE_GAME_ENGINE_DIR)/test

# Creates directory and runs cmake to build the project
build-core-game-engine:
	@echo "[INFO] Building 'core-game-engine'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(CORE_GAME_ENGINE_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(CORE_GAME_ENGINE_TEST_DIR) ; \
	mkdir -p $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	cd $(CORE_GAME_ENGINE_BUILD_DIR) && cmake ../$(CORE_GAME_ENGINE_DIR)

# Compiles the C++ code for the project
compile-core-game-engine:
	@echo "[INFO] Compiling 'core-game-engine'" ; \
	$(MAKE) -C $(CORE_GAME_ENGINE_BUILD_DIR) --silent

# Runs the test-suite
test-core-game-engine:
	@echo "[INFO] core-game-engine tests commencing..." ; \
	cd $(CORE_GAME_ENGINE_BUILD_DIR) && bin/tests-core-game-engine

#******************************
# 		GAME CONTAINER
#******************************

GAME_CONTAINER_DIR := $(APP_DIR)/game-container
GAME_CONTAINER_BUILD_DIR := game-container-build
GAME_CONTAINER_TEST_DIR := $(GAME_CONTAINER_DIR)/test

# Creates directory and runs cmake to build the project
build-game-container:
	@echo "[INFO] Building 'game-container'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(GAME_CONTAINER_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(GAME_CONTAINER_TEST_DIR) ; \
	mkdir -p $(GAME_CONTAINER_BUILD_DIR) ; \
	cd $(GAME_CONTAINER_BUILD_DIR) && cmake ../$(GAME_CONTAINER_DIR)

# Compiles the C++ code for the project
compile-game-container:
	@echo "[INFO] Compiling 'game-container'" ; \
	$(MAKE) -C $(GAME_CONTAINER_BUILD_DIR) --silent

# Runs the test-suite
test-game-container:
	@echo "[INFO] game-container tests commencing..." ; \
	$(GAME_CONTAINER_BUILD_DIR)/bin/tests-game-container

#******************************
# 	 GAME CONTAINER MANAGER
#******************************

GAME_CONTAINER_MANAGER_DIR := $(APP_DIR)/game-container-manager
GAME_CONTAINER_MANAGER_BUILD_DIR := game-container-manager-build
GAME_CONTAINER_MANAGER_TEST_DIR := $(GAME_CONTAINER_MANAGER_DIR)/test

# Creates directory and runs cmake to build the project
build-game-container-manager:
	@echo "[INFO] Building 'game-container-manager'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(GAME_CONTAINER_MANAGER_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(GAME_CONTAINER_MANAGER_TEST_DIR) ; \
	mkdir -p $(GAME_CONTAINER_MANAGER_BUILD_DIR) ; \
	cd $(GAME_CONTAINER_MANAGER_BUILD_DIR) && cmake ../$(GAME_CONTAINER_MANAGER_DIR)

# Compiles the C++ code for the project
compile-game-container-manager:
	@echo "[INFO] Compiling 'game-container-manager'" ; \
	$(MAKE) -C $(GAME_CONTAINER_MANAGER_BUILD_DIR) --silent

# Runs the test-suite
test-game-container-manager:
	@echo "[INFO] game-container-manager tests commencing..." ; \
	cd $(GAME_CONTAINER_MANAGER_BUILD_DIR) && bin/tests-game-container-manager


#******************************
# 			NETWORKING
#******************************
# [INFO] No test suite for this module

NETWORKING_DIR := $(APP_DIR)/client-server-communication
NETWORKING_BUILD_DIR := client-server-communication-build

# Creates directory and runs cmake to build the project
build-networking:
	@echo "[INFO] Building 'networking'" ; \
	mkdir -p $(NETWORKING_BUILD_DIR) ; \
	cd $(NETWORKING_BUILD_DIR) && cmake ../$(NETWORKING_DIR)

# Compiles the C++ code for the project
compile-networking:
	@echo "[INFO] Compiling 'networking'" ; \
	$(MAKE) -C $(NETWORKING_BUILD_DIR) --silent

#******************************
# 	 		SERVER
#******************************

SERVER_DIR := $(APP_DIR)/server-platform
SERVER_BUILD_DIR := server-platform-build
SERVER_TEST_DIR := $(SERVER_DIR)/test

# Creates directory and runs cmake to build the project
build-server:
	@echo "[INFO] Building 'server'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(SERVER_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(SERVER_TEST_DIR) ; \
	mkdir -p $(SERVER_BUILD_DIR) ; \
	cd $(SERVER_BUILD_DIR) && cmake ../$(SERVER_DIR)

# Compiles the C++ code for the project
compile-server:
	@echo "[INFO] Compiling 'server'" ; \
	$(MAKE) -C $(SERVER_BUILD_DIR) --silent

# Runs the test-suite
test-server:
	@echo "[INFO] server tests commencing..." ; \
	cd $(SERVER_BUILD_DIR) && bin/tests-server

#******************************
#		SERVER MANAGER
#******************************
# cannot build as independent component, only available through integrated build

#******************************
#		SOCIAL GAMING
#******************************

SOCIAL_GAMING_DIR := $(APP_DIR)
SOCIAL_GAMING_BUILD_DIR := social-gaming-build

# Creates directory and runs cmake to build the project
build-social-gaming:
	@echo "[INFO] Building 'social-gaming'" ; \
	mkdir -p $(SOCIAL_GAMING_BUILD_DIR) ; \
	cd $(SOCIAL_GAMING_BUILD_DIR) && cmake ../$(SOCIAL_GAMING_DIR)

# Compiles the C++ code for the project
compile-social-gaming:
	@echo "[INFO] Compiling 'social-gaming'" ; \
	$(MAKE) -C $(SOCIAL_GAMING_BUILD_DIR) --silent

# Executes the code
run-client:
	@echo "[INFO] Running 'client'" ; \
	$(CLIENT_BUILD_DIR)/client

run-social-gaming:
	@echo "[INFO] Running 'social-gaming'" ; \
	$(SOCIAL_GAMING_BUILD_DIR)/bin/social-gaming

test-social-gaming:
	@echo "[INFO] all tests commencing..."
	cd $(SOCIAL_GAMING_BUILD_DIR) ; \
	bin/tests-client ; \
	bin/tests-core-game-engine ; \
	bin/tests-game-container ; \
	bin/tests-game-container-manager ; \
	bin/tests-server

#******************************
#	   MESSAGE PROCESSORS
#******************************

MESSAGE_PROCESSORS_DIR := message-processors
MESSAGE_PROCESSORS_BUILD_DIR := message-processors-build
MESSAGE_PROCESSORS_TEST_DIR := $(MESSAGE_PROCESSORS_DIR)/test

# Creates directory and runs cmake to build the project
build-message-processors:
	@echo "[INFO] Building 'message-processors'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(MESSAGE_PROCESSORS_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(MESSAGE_PROCESSORS_TEST_DIR) ; \
	mkdir -p $(MESSAGE_PROCESSORS_BUILD_DIR) ; \
	cd $(MESSAGE_PROCESSORS_BUILD_DIR) && cmake ../$(MESSAGE_PROCESSORS_DIR)

# Compiles the C++ code for the project
compile-message-processors:
	@echo "[INFO] Compiling 'message-processors'" ; \
	$(MAKE) -C $(MESSAGE_PROCESSORS_BUILD_DIR) --silent

# Runs the test-suite
test-message-processors:
	@echo "[INFO] message-processors tests commencing..." ; \
	cd $(MESSAGE_PROCESSORS_BUILD_DIR) && bin/tests-message-processors

#******************************
# 			GENERIC
#******************************

# [INFO]: Runs by default if 'make' has no target 
all:
	$(info 'all' is disable by default...)
	$(info 'make help')


# [INFO]: Display helpful information in CLI
help:
	$(info [INFO] To execute commands, type 'make' followed by any of commands below:)
	$(info *************************************)
	$(info 1. build-social-gaming)
	$(info 2. compile-social-gaming)
	$(info 3. test-{{ name }})
	$(info *************************************)


# [INFO]: Removes Build & Test artifacts
clean: 
	@echo "[INFO] Removing Build Directories..."
	@rm -rf *-build
	@echo "[INFO] Removing gtest from Directories..."
	@rm -rf $(CLIENT_TEST_DIR)/gtest
	@rm -rf $(CORE_GAME_ENGINE_TEST_DIR)/gtest
	@rm -rf $(GAME_CONTAINER_TEST_DIR)/gtest
	@rm -rf $(GAME_CONTAINER_MANAGER_TEST_DIR)/gtest
	@rm -rf $(SERVER_TEST_DIR)/gtest
	
# [INFO]: Build all the applications separately 
all-build: build-client build-client-server-communication build-core-game-engine build-game-container build-game-container-manager build-server build-social-gaming

# [INFO]: Compile all the applications separately 
all-compile: compile-client compile-client-server-communication compile-core-game-engine compile-game-container compile-game-container-manager compile-server compile-social-gaming

# [INFO]: Runs all the tests separately 
all-tests: test-client test-core-game-engine test-game-container test-game-container-manager test-server test-social-gaming