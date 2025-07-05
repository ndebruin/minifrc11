#include "States.h"

void Coast::initialize_impl() {
  prevAltitude = this->ctx->baro.getData()->altitude;
}

State *Coast::loop_impl() {
  // FIXME: Some sort of active airbrake control here

  const auto baroData = ctx->baro.getData();

  if (lastBaroReadingTime != baroData.getLastUpdated()) {
    lastBaroReadingTime = baroData.getLastUpdated();

    ewma.update((baroData->altitude - prevAltitude) * (::millis() - lastBaroReadingTime) / 1000.);
    if (velDebouncer.update(std::abs(ewma.getAvg()) < APOGEE_VEL_THRESHHOLD, ::millis())) {
      return new DrogueDescent(this->ctx);
    }
  }

  if (this->currentTime >= COAST_MAX_TIME) {
    ctx->errorLogFile.printf("[%d] Coast state timed out\n", ::millis());
    return new DrogueDescent(this->ctx);
  }
  return nullptr;
}