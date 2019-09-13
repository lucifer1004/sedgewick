BUILDDIR := build

build:
	@meson $(BUILDDIR) && cd $(BUILDDIR) && ninja

clean:
	@rm -r $(BUILDDIR)

.PHONY: build, clean