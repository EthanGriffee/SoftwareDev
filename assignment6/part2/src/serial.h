#pragma once

/**
 * Interface for serializeing and desserializing data
 * */
class Serialize {

    public:

        /**
         * returns a char* representation of the Object.
         * */
        virtual char* serialize() {}
};