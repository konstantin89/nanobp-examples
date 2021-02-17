ECHO OFF

ECHO "Generating NanoPb autogen files"

pip install protobuf grpcio-tools

python external/nanopb-0.4.4-windows-x86/generator/nanopb_generator.py ExampleMessage.proto --output-dir=src/auto_generated