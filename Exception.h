//
// Created by yahav on 23/11/2017.
//

#ifndef WET_1_EXCEPTIONS_H
#define WET_1_EXCEPTIONS_H

#include <stdexcept>

namespace SplayTreeExceptions {
    class ElementNotFound : public std::runtime_error {
    public:
        ElementNotFound() : std::runtime_error("Element not found") {}
    };

    class ElementAlreadyExists : public std::runtime_error {
    public:
        ElementAlreadyExists() : std::runtime_error("Element already exists") {}
    };

    class EmptyTree : public std::runtime_error {
    public:
        EmptyTree() : std::runtime_error("Tree is Empty") {}
    };
    class AllocationError : public std::runtime_error {
    public:
        AllocationError() : std::runtime_error("Allocation Error") {}
    };
}
namespace ListExceptions {
    class ElementNotFound : public std::runtime_error {
    public:
        ElementNotFound() : std::runtime_error("Element not found") {}
    };
}

namespace GladiatorExceptions {
    class GladiatorAlreadyExists : public std::runtime_error {
    public:
        GladiatorAlreadyExists() : std::runtime_error("Gladiator already exists") {}
    };
    class GladiatorNotFound : public std::runtime_error {
    public:
        GladiatorNotFound() : std::runtime_error("Gladiator does not found") {}
    };
}

namespace TrainerExceptions {
    class TrainerAlreadyExists : public std::runtime_error {
    public:
        TrainerAlreadyExists() : std::runtime_error("Trainer already exists") {}
    };
    class TrainerNotFound : public std::runtime_error {
    public:
        TrainerNotFound() : std::runtime_error("Trainer does not found") {}
    };
    class AllocationError : public std::runtime_error {
    public:
        AllocationError() : std::runtime_error("Allocation Error") {}
    };
}

namespace ColosseumExceptions {
    class InvalidInput : public std::runtime_error {
    public:
        InvalidInput() : std::runtime_error("Input is not valid") {}
    };
    class Failure : public std::runtime_error {
    public:
        Failure() : std::runtime_error("Failure") {}
    };
    class Allocation_Error : public std::runtime_error {
    public:
        Allocation_Error() : std::runtime_error("Allocation Error") {}
    };
    class AlreadyExists : public std::runtime_error {
    public:
        AlreadyExists() : std::runtime_error("AlreadyExists") {}
    };
}

namespace HeapExceptions {
    class InvalidInput : public std::runtime_error {
    public:
        InvalidInput() : std::runtime_error("Input is not valid") {}
    };
    class Failure : public std::runtime_error {
    public:
        Failure() : std::runtime_error("Failure") {}
    };
    class Allocation_Error : public std::runtime_error {
    public:
        Allocation_Error() : std::runtime_error("Allocation Error") {}
    };
}

namespace HashExceptions {
    class Allocation_Error : public std::runtime_error {
    public:
        Allocation_Error() : std::runtime_error("Allocation Error") {}
    };
    class AlreadyExists : public std::runtime_error {
    public:
        AlreadyExists() : std::runtime_error("Already Exists") {}
    };
}

#endif //WET_1_EXCEPTIONS_H