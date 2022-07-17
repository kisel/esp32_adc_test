uint16_t adcReadMultisampl(unsigned pin, unsigned samples_count) {
    // get average from multi-sampling
    unsigned samples = samples_count;
    uint32_t sum = 0;

    // pinMode(pin, INPUT);
    for (unsigned i = 0; i < samples; ++i) {
        delay(1);
        sum += analogRead(pin);
    }
    return sum / samples; // 0..4096
}

void loop()
{
    char buf[512];
    char *cursor = buf;
    unsigned pin = PIN;
    cursor += sprintf(cursor, "pin36");
    for (unsigned atten = 0; atten < 4; atten++) {
        analogSetPinAttenuation(pin, (adc_attenuation_t)atten);
        delay(10);
        unsigned res = analogRead(pin);
        cursor += sprintf(cursor, " att%u= %5u", atten, (unsigned)res);
        cursor += sprintf(cursor, " att%u_avg64= %5u", atten, (unsigned)adcReadMultisampl(pin, 64));
        cursor += sprintf(cursor, " att%u_avg256= %5u", atten, (unsigned)adcReadMultisampl(pin, 256));
    }
    cursor += sprintf(cursor, " msampl64= %5u", (unsigned)adcReadMultisampl(pin, 64));

    //theApp->mainloop();
    Serial.println(buf);
    delay(100);
}

