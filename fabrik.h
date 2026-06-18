#ifndef FABRIK_H
#define FABRIK_H

#include "vector.h"
#include <vector>
#include <cmath>

class Fabrik
{
public:
    float tolerance = 0.001f;
    int max_iters = 10;

    std::vector<Vector3> joint_positions;
    std::vector<float> segment_lengths;

    void init(const std::vector<float>& in_lengths)
    {
        segment_lengths = in_lengths;
        joint_positions.resize(in_lengths.size() + 1, Vector3(0, 0, 0));
    }

    bool solve(const Vector3& anchor, const Vector3& target)
    {
        if (joint_positions.empty())
        {
            return false;
        }

        float total_reach = 0.0f;
        for (float l : segment_lengths)
        {
            total_reach += l;
        }

        Vector3 dir = target - anchor;
        float dist = vec_length(dir);
        if (dist > total_reach - 0.001f)
        {
            Vector3 d = (dist > 0.001f) ? normalize(dir) : Vector3(0, -1, 0);
            joint_positions[0] = anchor;

            for (int i = 0; i < (int)segment_lengths.size(); i++)
            {
                joint_positions[i + 1] = joint_positions[i] + d * segment_lengths[i];
            }

            return false;
        }

        joint_positions[0] = anchor;

        for (int iter = 0; iter < max_iters; iter++)
        {
            joint_positions.back() = target;

            for (int i = (int)joint_positions.size() - 2; i >= 0; i--)
            {
                Vector3 d = joint_positions[i] - joint_positions[i + 1];
                float len = vec_length(d);

                if (len < 0.0001f)
                {
                    d = Vector3(0, 1, 0);
                }
                else
                {
                    d = d * (1.0f / len);
                }

                joint_positions[i] = joint_positions[i + 1] + d * segment_lengths[i];
            }

            joint_positions[0] = anchor;

            for (int i = 0; i < (int)joint_positions.size() - 1; i++)
            {
                Vector3 d = joint_positions[i + 1] - joint_positions[i];
                float len = vec_length(d);

                if (len < 0.0001f)
                {
                    d = Vector3(0, -1, 0);
                }
                else
                {
                    d = d * (1.0f / len);
                }

                joint_positions[i + 1] = joint_positions[i] + d * segment_lengths[i];
            }

            Vector3 diff = joint_positions.back() - target;
            if (vec_length(diff) < tolerance)
            {
                return true;
            }
        }

        return false;
    }
};

#endif