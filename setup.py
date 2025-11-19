from setuptools import setup

# usage
# python setup.py develop --user
# python setup.py develop --uninstall --user

setup(
    name='calibration-manager',
    author='Chenzhe Qian',
    author_email='chenzhe.qian@tusimple.ai',
    description='calibration files reader',
    classifiers=['Private :: Do Not Upload'],
    install_requires=['numpy', 'pyyaml'],
    packages=['calibration_manager']
)
