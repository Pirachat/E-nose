#pragma once
#include <stdarg.h>
#define NUM_FEATURES 6
#define NUM_TARGET 7
namespace Eloquent {
    namespace ML {
        namespace Port {
            class LogisticRegression {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float votes[NUM_TARGET] = { 0.0f };
                        votes[0] = dot(x,NUM_FEATURES,   -0.006205340932  , -0.094051098209  , -0.157012199862  , -0.016044697299  , 0.038453957262  , -0.012145719927 ) + 60.04403063049981;
                        votes[1] = dot(x,NUM_FEATURES,   -0.056835170614  , -0.026787651679  , 0.088964013691  , 0.037125302139  , -0.047510305735  , -0.071506967471 ) + 7.6464053129490095;
                        votes[2] = dot(x,NUM_FEATURES,   -0.139849636185  , 0.036415148376  , 0.012130388517  , -0.035779706923  , 0.069356233308  , -0.00414053503 ) + 30.579860395296027;
                        votes[3] = dot(x,NUM_FEATURES,   -0.002865382054  , 0.034876570415  , 0.049597385916  , -0.06622745194  , 0.0308623076  , 0.074265550766 ) + -17.320487766575475;
                        votes[4] = dot(x,NUM_FEATURES,   0.11995331332  , -0.018975235027  , 0.005939081887  , -0.041992759322  , -0.069970824927  , 0.002052355962 ) + 21.198442414499596;
                        votes[5] = dot(x,NUM_FEATURES,   0.135733296763  , 0.007793158564  , 0.006135865856  , 0.052490284948  , -0.068773325252  , 0.018428110602 ) + -46.81457847830283;
                        votes[6] = dot(x,NUM_FEATURES,   -0.049931072831  , 0.060729114722  , -0.005754518828  , 0.070429047626  , 0.047581966523  , -0.006952789239 ) + -55.33367253373744;
                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < NUM_TARGET; i++) {
//                            Serial.print(" ");
//                            Serial.print(votes[i]);
//                            Serial.print(" ");
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "background";
                            case 1:
                            return "lighter";
                            case 2:
                            return "cigarette";
                            case 3:
                            return "insecticide";
                            case 4:
                            return "rotten";
                            case 5:
                            return "al";
                            case 6:
                            return "pipe";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                    /**
                    * Compute dot product
                    */
                    float dot(float *x,int size,...) {
                        va_list w;
                        va_start(w, size);
                        float dot = 0.0;

                        for (uint16_t i = 0; i < size; i++) {
                            const float wi = va_arg(w, double);
                            dot += x[i] * wi;
                        }

                        return dot;
                    }
                };
            }
        }
    }
