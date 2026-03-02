ALSO += .peru/lastimports .WAIT

.peru/lastimports: peru.yaml
	@echo "Peru Syncing..."
	@peru sync || (echo "BIG WARNING OF DOOM: Your system lacks a functioning peru or something is majorly wrong, we'll ignore that and move on as this repo is unified"; true)
	@touch $@
