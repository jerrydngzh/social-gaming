#******************************
# 		CONFIGURATIONS
#******************************
ROOT_DIR := $(pwd)

#******************************
#		MESSAGE (TEST)
#******************************

MESSAGE_DIR := message
MESSAGE_BUILD_DIR := message-build

.PHONY: build-message

# creates new directory, runs cmake, and then builds the application by calling makefile rendered from cmake
build-message:
	@echo "[INFO] Building 'Message'" ; \
	rm -rf $(MESSAGE_BUILD_DIR) ; \
	mkdir $(MESSAGE_BUILD_DIR) ; \
	cd $(MESSAGE_BUILD_DIR) && cmake ../$(MESSAGE_DIR)
	@$(MAKE) -C $(MESSAGE_BUILD_DIR) --silent

test-message: build-message
	@cd $(MESSAGE_BUILD_DIR) && test/runAllTests


#******************************
# 			ALL
#******************************

all:
	$(info "[INFO] all disabled...")


all-tests: test-message