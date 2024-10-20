# Abre el archivo hexadecimal que contiene los datos como texto
with open("flecha_ab.txt", "r") as hex_file:
    hex_data = hex_file.read().replace("0x", "").replace(",", "").split()

# Convierte los datos a binario
binary_data = bytearray([int(byte, 16) for byte in hex_data])

# Guarda los datos binarios en un archivo .bin
with open("flecha_ab.bin", "wb") as bin_file:
    bin_file.write(binary_data)

print("Archivo binario generado: fondo.bin")
