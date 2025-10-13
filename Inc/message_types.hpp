/*
 * message_types.hpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#ifndef INC_MESSAGE_TYPES_HPP_
#define INC_MESSAGE_TYPES_HPP_

#define MESSAGE_SIZE 5
#define ERROR_SIZE 5

#include <cstdint> // Para uint8_t
#include <cstring>  // Para std::string

// Definición del struct. Importante: no usar std::string directamente aquí
// en un struct que será enviado byte a byte, ya que std::string
// es un objeto complejo con punteros. Usamos arrays de char fijos.
struct StructMessage {
    char group;           // 1 byte
    char subgroup;        // 1 byte
    uint16_t id;
    uint16_t step;
    char end;
};

// Funciones para serializar/deserializar
// Devuelve el número de bytes serializados (sizeof(StructMensaje))
size_t serialize_message(const StructMessage& msg, uint8_t* buffer, size_t buffer_size);

// Devuelve el número de bytes deserializados (sizeof(StructMensaje))
size_t deserialize_message(const uint8_t* buffer, StructMessage& msg, size_t buffer_size);





#endif /* INC_MESSAGE_TYPES_HPP_ */
