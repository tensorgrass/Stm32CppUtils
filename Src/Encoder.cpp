#include <Encoder.hpp>

Encoder::Encoder(TIM_HandleTypeDef *htim_value)
    : htim(htim_value) {
  // Constructor implementation
}

Encoder::~Encoder() {
  // Destructor implementation
}

void Encoder::init() {
  HAL_TIM_Encoder_Start_IT(htim, TIM_CHANNEL_ALL);
}

uint32_t Encoder::getValue() {
  uint32_t value = __HAL_TIM_GET_COUNTER(htim);
  return value;
}

int32_t Encoder::getDifferenceSigned(uint32_t previous_value) {
  uint32_t current_value = getValue();
  uint32_t diff_right = (current_value >= previous_value) ? (current_value - previous_value) : (MODULE + current_value - previous_value); // Diferencia hacia la derecha (a - b)
  uint32_t diff_left  = (previous_value >= current_value) ? (previous_value - current_value) : (MODULE + previous_value - current_value); // Diferencia hacia la izquierda (b - a)

  int32_t diff_signed_min;
  if (diff_right <= diff_left) {
      diff_signed_min = diff_right; // positivo: a está a la derecha de b
  } else {
      diff_signed_min = -static_cast<int32_t>(diff_left); // negativo: a está a la izquierda de b
  }
  return diff_signed_min;
}

uint32_t Encoder::getDifferenceUnsigned(uint32_t previous_value) {
  uint32_t current_value = getValue();
  uint32_t diff_right = (current_value >= previous_value) ? (current_value - previous_value) : (MODULE + current_value - previous_value); // Diferencia hacia la derecha (a - b)
  uint32_t diff_left  = (previous_value >= current_value) ? (previous_value - current_value) : (MODULE + previous_value - current_value); // Diferencia hacia la izquierda (b - a)
  uint32_t diff_min   = (diff_right < diff_left) ? diff_right : diff_left;
  return diff_min;
}
