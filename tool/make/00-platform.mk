ifeq ($(shell uname), Darwin)
  PLATFORM = Mac
else
  PLATFORM = Linux
endif
$(info Platform: $(PLATFORM))
