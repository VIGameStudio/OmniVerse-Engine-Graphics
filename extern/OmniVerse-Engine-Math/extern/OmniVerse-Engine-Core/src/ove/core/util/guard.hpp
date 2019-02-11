#pragma once

/**
 * TODO:
 * Revise
 */

struct nocopy {
protected:
    nocopy() = default;
    ~nocopy() = default;

private:
    nocopy(const nocopy&) = delete;
    nocopy& operator=(const nocopy&) = delete;
};
