ALSO += .peru/lastimports .WAIT

HAS_PERU := 0
ifneq ($(shell which peru 2> /dev/null),)
        HAS_PERU := 1
endif

.peru/lastimports: peru.yaml
	@echo "Peru Syncing..."
	@peru sync 2>/dev/null ||\
        (echo "NOTICE:\nYour system lacks <https://github.com/buildinspace/peru>\nPreunified build will continue."; true)
	@touch $@ 2>/dev/null || true
