# Bayes Classifier

## About

Harness the dark art of [Bayes' Theorem](https://en.wikipedia.org/wiki/Bayes%27_theorem) to dictate your every move. Or something like that. In seriousness, this is a naive Bayes classifier that can be used for binary decision making, such as whether or not to take an action.

The basic components of the classifier are **Conditions**, **Observations**, and **Outcomes**.

Conditions are essentially the values the classifier takes into account when making a decision. They can be either **Discrete** or **Continuous** conditions. Discrete conditions are conditions with a finite number of values, such as booleans and enums. Continuous conditions are conditions with values that fall into a range. Both types of conditions store data that is used to determine the probability of contributing to a decision.

Observations are containers that hold a value for each condition. If a classifier has 1 discrete and 2 continuous conditions, the observation will have 1 discrete and 2 continuous values. The classifier can test an observation and will make a decision based on the values it contains. The classifier can also store observations, which will contribute to the decision for an observation being tested. Observations also store an outcome. The outcome of the observation is the end result. It is used only if an observation is stored, not used when an it is tested.

An outcome is a simple success or failure. When an observation is stored, the outcome of that observation influences how the values weigh against future decisions. For instance, let's say the outcome of an observation is a failure and one of its discrete conditions, "Condition 1", was 0. If that observation is saved, when testing future observations, the classifier would be less likely to return true if the value of "Condition 1" was 0. Thus, outcomes can be used for machine learning and encourage/discourage certain behavior. As an example, in a game setting, if the classifier decided for an NPC to take an action and the NPC was killed, the outcome of that NPC's observation could be set to failure and saved. Then all other NPCs using the same classifier would be less likely to take a similar action under the same conditions.

## Using the Classifier

Installation is as simple as dropping the files from the [src](https://github.com/Nolnocn/Bayesian-Inference/tree/master/src) directory into a C++ project and going to town.

Using the classifier takes only 3 steps:
1. Set the Conditions
2. Create an Observation
3. Test the Obseration

Optionally, the observation can also be saved to weigh in on future decisions. Check out the [demo](https://github.com/Nolnocn/Bayesian-Inference/tree/master/demo) for a sample code of usage.

Side note: This is a C++ version of (and improvement upon) the classifier I created for an AI project, [Siege](https://github.com/Nolnocn/Siege/tree/master/Assets/Scripts/Bayes).
