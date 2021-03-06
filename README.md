# nanobp-example

## Brief

POC of Protobuf encoder and decoder applications implemented with NanoPb.   


</br>

## Links

[Download nanopb library](https://jpa.kapsi.fi/nanopb/download/)  
[Nanopb official examples](https://github.com/nanopb/nanopb/tree/master/examples)   
[Nanopb reference](https://android.googlesource.com/platform/external/nanopb-c/+/lollipop-dev/docs/concepts.rst)  
 [Example: Pack repeated fields with Nanopb library](https://gist.github.com/vpetrigo/df85bbb8197e3be76f644bb8290444c4) 

</br>

## NanoPb autogen files generation

`compile_proto.bat` script is used to compile the `ExampleMessage.proto` proto  
file to C source and header files.  

`compile_proto.bat` should be run automatically by the Cmake file in the  
root of the project.    

</br>

## Encoder application

`build/encoder` application creates and example proto message.   
Then it encodes it, and writes the excoded message to binary file.  

The produced binary file then can be decoded by the decoder app.

</br>

## Decoder application

`build/decoder` application is used to read the encoded message from binary  
file, decode it and print the message to std::out.  

Example output:
``` text
ExampleMessage content
message.number=3
message.str=str
message.str_array[0]=first
message.str_array[1]=second
message.sub_message_array[0]=6, sub_str_1
message.sub_message_array[1]=7, sub_str_2
```

</br>

