
dot_files = $(shell find build/dot -name "*.dot")
pdf_files = $(patsubst build/dot/%.dot,build/dot/pdf/%.pdf,$(dot_files))
png_files = $(patsubst build/dot/%.dot,build/dot/png/%.png,$(dot_files))

all:
	pbs2 make config.py

doc:
	pbs2 make config.py doc

build/dot/pdf/%.pdf: build/dot/%.dot
	@mkdir -p $(dir $@)
	@bash build_dot.bash $< '-Tpdf -o$@ $^'
	#neato -Tpdf -o$@ $^
	#dot -Tpdf -o$@ $^
	#fdp -Tpdf -o$@ $^

build/dot/png/%.png: build/dot/%.dot
	@mkdir -p $(dir $@)
	@bash build_dot.bash $< '-Tpng -o$@ $^'

dot: $(pdf_files)

png: $(png_files)

dotclean:
	rm -rf build/dot/pdf

clean:
	rm -rf build/object/*
	rm -rf build/process/*

