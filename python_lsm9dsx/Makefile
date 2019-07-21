PY=python

python_interface:
	$(PY) setup.py sdist
	cp ../README.md .

install:
	pip install dist/*

uninstall:
	pip uninstall lsm9dsx

.PHONY: clean

clean:
	rm -f README.md
	rm -rf dist
	rm -rf *.egg-info
