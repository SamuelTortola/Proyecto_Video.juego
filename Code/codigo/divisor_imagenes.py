from PIL import Image

def rgb_to_rgb565(r, g, b):
    """Convierte un color RGB a formato RGB565."""
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

def convert_image_to_rgb565(image_path, output_path):
    """Convierte una imagen a formato RGB565 y la guarda en un archivo binario."""
    # Cargar la imagen y convertirla a RGB
    img = Image.open(image_path).convert('RGB')
    pixels = img.load()

    # Crear un archivo binario para guardar los datos en formato RGB565
    with open(output_path, 'wb') as f:
        for y in range(img.height):
            for x in range(img.width):
                r, g, b = pixels[x, y]  # Obtener los valores RGB
                rgb565 = rgb_to_rgb565(r, g, b)  # Convertir a RGB565
                # Escribir los dos bytes de RGB565
                f.write(rgb565.to_bytes(2, byteorder='big'))

    print(f"Imagen convertida a RGB565 y guardada en {output_path}")

# Convertir la imagen completa a RGB565
convert_image_to_rgb565('1Jugador.jpg', 'Game_over_rgb565.bin')


def convert_and_split_image_to_rgb565(image_path, part1_output, part2_output):
    """Convierte y divide una imagen a RGB565 en dos partes."""
    # Cargar la imagen y convertirla a RGB
    img = Image.open(image_path).convert('RGB')
    
    # Dividir la imagen en dos partes
    part1 = img.crop((0, 0, 240, 250))  # Parte 1: 240x250
    part2 = img.crop((0, 250, 240, 320))  # Parte 2: 240x70
    
    # Convertir y guardar la primera parte
    with open(part1_output, 'wb') as f:
        pixels = part1.load()
        for y in range(part1.height):
            for x in range(part1.width):
                r, g, b = pixels[x, y]
                rgb565 = rgb_to_rgb565(r, g, b)
                f.write(rgb565.to_bytes(2, byteorder='big'))

    # Convertir y guardar la segunda parte
    with open(part2_output, 'wb') as f:
        pixels = part2.load()
        for y in range(part2.height):
            for x in range(part2.width):
                r, g, b = pixels[x, y]
                rgb565 = rgb_to_rgb565(r, g, b)
                f.write(rgb565.to_bytes(2, byteorder='big'))

    print(f"Imagen dividida y convertida a RGB565: {part1_output}, {part2_output}")

# Dividir y convertir la imagen a RGB565
convert_and_split_image_to_rgb565('1Jugador.jpg', '1Jugador1.bin', '1Jugador2.bin')
