#******************************
# 		CONFIGURATIONS
#******************************
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
	rm -rf $(MESSAGE_BUILD_DIR)


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
	@echo "[INFO] Building 'Message'" ; \
	rm -rf $(MESSAGE_BUILD_DIR) ; \
	mkdir $(MESSAGE_BUILD_DIR) ; \
	cd $(MESSAGE_BUILD_DIR) && cmake ../$(MESSAGE_DIR)
	@$(MAKE) -C $(MESSAGE_BUILD_DIR) --silent


# [INFO]: Run the Test Suite for 'message'
test-message:
	@cd $(MESSAGE_BUILD_DIR) && test/runAllTests
