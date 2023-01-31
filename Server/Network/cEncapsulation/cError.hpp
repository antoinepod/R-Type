//
// Created by pan on 19/01/23.
//

#pragma once

#include <exception>
#include <string>

namespace RType {
    class SocketError : public std::exception {
    private:
        std::string _message;

    public:
        explicit SocketError(std::string message) : _message(std::move(message)) {};

        [[nodiscard]] const char *what() const noexcept override {
                return _message.c_str();
        }
    };

    class BindingError : public std::exception {
        private:
            std::string _message;

        public:
            explicit BindingError(std::string message) : _message(std::move(message)) {};

            [[nodiscard]] const char *what() const noexcept override {
                return _message.c_str();
            }
    };
}