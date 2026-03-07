HELP_ME += \
"00-platform\n" \
"provides PLATFORM, which is currently only designed for Linux and MacOS\n" \
"On MacOS: \"Mac\"\n" \
"On Linux: \"Linux\"\n" \
"Will always print operating system ('Platform: Linux' text).\n" \
"Assumes Linux by default.\n" \
"\n"

ifeq ($(shell uname), Darwin)
  PLATFORM = Mac
else
  PLATFORM = Linux
endif
$(info Platform: $(PLATFORM))
