#******************************
# 		CONFIGURATIONS
#******************************
CORE_GAME_ENGINE_DIR := core-game-engine
CORE_GAME_ENGINE_BUILD_DIR := core-game-engine-build
MESSAGE_DIR := message
MESSAGE_BUILD_DIR := message-build
ROOT_DIR := $(pwd)


#******************************
# 			GENERIC
#******************************

# [INFO]: Runs by default if 'make' has no target 
all:
	$(info 'all' is disable by default...)


# [INFO]: Display helpful information in CLI
help:
	$(info *************************************)
	$(info 1. [BUILDING]: build-{{ application }})
	$(info 2. [TESTING] : test-{{ application }})
	$(info *************************************)


# [INFO]: Removes Build Directories
clean: 
	@echo "[INFO] Removing Build Directories..." ; \
	rm -rf $(MESSAGE_BUILD_DIR) ; \
	rm -rf $(CORE_GAME_ENGINE_BUILD_DIR)


# [INFO]: Runs all the tests
all-tests: test-message


#******************************
#		MESSAGE (TEST)
#******************************

# [INFO]: 
#	1. Creates new directory
#   2. Runs cmake
#	3. Builds the application by calling nested makefile
build-message:
	@echo "[INFO] Running CMake on 'message'" ; \
	rm -rf $(MESSAGE_BUILD_DIR) ; \
	mkdir $(MESSAGE_BUILD_DIR) ; \
	cd $(MESSAGE_BUILD_DIR) && cmake ../$(MESSAGE_DIR)
	@echo "[INFO] Running Build on 'message'" ; \
	$(MAKE) -C $(MESSAGE_BUILD_DIR) --silent


# [INFO]: Run the Test Suite for 'message'
test-message:
	@cd $(MESSAGE_BUILD_DIR) && test/runAllTests


#******************************
#	CORE GAME ENGINE (TEST)
#******************************

build-core-game-engine:
	@echo "[INFO] Building 'core-game-engine'" ; \
	rm -rf $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	mkdir $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	cd $(CORE_GAME_ENGINE_BUILD_DIR) && cmake ../$(CORE_GAME_ENGINE_DIR)
	@echo "[INFO] Running Build on 'core-game-engine'" ; \
	$(MAKE) -C $(CORE_GAME_ENGINE_BUILD_DIR) --silent

run-core-game-engine:
	@echo "[INFO] Running 'core-game-engine'" ; \
	$(CORE_GAME_ENGINE_BUILD_DIR)/bin/demo $(CORE_GAME_ENGINE_BUILD_DIR)/game-files/rock-paper-scissors.game

test-game-engine:
	@echo "TODO"