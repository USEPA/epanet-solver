# EPANET Contributors Guide

Thank you for taking the time to look through these EPANET submission guidelines, and considering supporting this effort. All contributions are welcome, including bug reports, bug fixes, documentation improvements, and enhancements.

**Purpose**

The purpose of this guide is to orient potential contributors to the source code contribution and acceptance process for United States (U.S.) Environmental Protection Agency&#39;s (EPA&#39;s) EPANET software project. This guide briefly describes the testing framework, the copyright and license, steps in the contribution process,and answers some frequently asked questions.

**Quality Assurance and Quality Control (QA/QC)**

Quality assurance and quality control (QA/QC) are key to ensuring the software will run correctly. This is particularly important in an open-source environment. Code associated with new features in a contribution must include reproducible tests that verify and document that the software is working as intended. If your changes impact existing code that already has a testing component, you do not need to program a test (unless your new code is somehow causing an old test to fail—these cases will be considered individually if they occur). When merged with the current version of EPANET, contributed code must not cause regression error in features that were previously known to be working correctly. QA/QC testing must be reproducible and generate a permanent record for documentation purposes that describes the software under test, the test being run, and the result of the tests. To eliminate the burden of QA/QC related testing, EPA is pursuing a strategy of test automation utilizing Continuous Integration (CI) tools. Source code and tests from contributors should be written to integrate with the projects chosen CI toolchain (Appveyor, Travis CI, and Circle CI).

**Software Copyright and Licensing**

Software produced by EPA and its affiliates (i.e., any person under current contract/grant/cooperative agreement to the EPA) is considered a &quot;written work&quot; of the U.S. Federal Government and therefore resides in the public domain. EPA can, however, hold the copyrighted work of third parties. Third party contributors can therefore dedicate their work to the public domain, or copyright and license it. EPA will honor the license of a third-party contributor, provided it is suitable Open Source Initiative (OSI) approved open source license that does not conflict with those portions of the code base residing in the public domain or with licensed contributions made by other parties. Because EPANET has historically been released as public domain software, liberal open source (OS) licenses such as the MIT License or BSD License are preferred.

**Version Control**

The EPANET software projects use git distributed version control software to manage changes to the source code, developer documentation, and build configuration. GitHub is a web based platform for sharing git software repositories and the latest changes to the code with fellow developers. Git has many features that support code management in multi-developer teams. Git is powerful but can be complicated. It is well documented and many resources for learning how to use git and GitHub effectively are available online.

**Prerequisites for Contributors**

Groups of people with many talents working together make the best software. There are many ways to contribute to EPA&#39;s open source projects including, software development, technical writing, testing, submitting bugs, making feature requests, and helping fellow users. Because we use git and GitHub to manage software configuration and organize contributions, familiarity with these tools and the ability to effectively use them is a prerequisite to making contributions. The project wiki has git instructions for beginning contributors to make things easier.

If you are interested in contributing software, then you probably can already use git. In addition, it is useful to become familiar with the project build and configuration, developer guidelines, and software internals. You are welcome to learn all these things on your own, but it&#39;s a lot easier to learn and get things done by joining and working as part of a developer community.

**Step by Step Instructions for Software Contributors**

1. Join GitHub and visit the EPA GitHub site
2. Contact the maintainer of the GitHub repository and discuss the nature of contributions you have in mind.
3. If a similar issue in the GitHub repository does not already exist, create one describing your contribution and the problem it will solve or the feature it will implement. The merits of your contribution might be publically discussed by the community.
4. Configure git and initiate work on your bug fix or feature idea in your branch GitHub repository.
5. Adhere to development guidelines and coding standards in line with community norms.
6. Commit your code frequently to your branch GitHub repository and ask for input periodically.
7. Update the community on your progress.
8. When the code is ready, issue a pull request in git to the master GitHub repository.
9. Your contribution will be reviewed by the maintainer of the master GitHub repository prior to acceptance.
10. Address reviewer comments.
11. Maintainer might merge your pull request or provide feedback on how it can be improved.

**Documentation and User Manual Updates**

Updates to developer documentation and software User&#39;s Manuals must accompany source code contributions to explain what it does, how it interacts with other components, what it needs to function appropriate, and what it returns—as applicable. If the goal of a change is to fix a bug, the bug number should also be included in the code to help identify where those errors were. Documentation updates are required for approval. We are in the process of selecting tools and converting formats to better support community contributions to documentation.

**Criteria for Acceptance**

Does the contribution address a publically posted known issue within the repository?

Is your feature discussed in the project development roadmap?

What are the merits of the contribution?

Does the code adhere to development and code style guidelines adopted by the community?

Does the contribution adhere to quality assurance guidelines?

Is the contribution properly documented?

Does the contribution present a user training or support issue?

**Frequently Asked Questions**

_How can I become a contributor?_

Many opportunities exist for the community to become involved and contribute to the open source development of EPANET. The best way to become a contributor is to become active on the GitHub repository. You don&#39;t need to know anyone to get started. If you are an EPANET user and have a great idea for a new feature, share it as a feature request on the GitHub website. If you are an experienced user without knowledge of how to program, you contribute to the open source community by providing help with documentation. If you want to gain some programming experience, you could provide help with testing. If you know how to develop software and want to learn more about EPANET, you could provide fixes for bugs documented in the Issue tracker on the GitHub repository. If you are a modeling expert with software development experience, you can contribute a new feature.

_Which repo should I contribute to?_

Although the EPANET repositories at US EPA&#39;s Enterprise Site can and will accept pull requests from individuals wishing to support this effort, we encourage individual developers to submit pull requests to one of the community based repositories supporting this effort. In this way, the enterprise repository will house the source code and supporting files for major versions. While community based groups will contain active forums, bug reporting, and more frequent development activity. Major versions from the community groups will be submitted to this repository once they confirm with community contribution guidelines and are approved. The primary development activity for EPANET is occurring as part of the Open Water Analytics community development group ( [https://github.com/OpenWaterAnalytics/EPANET](https://github.com/OpenWaterAnalytics/EPANET), [http://wateranalytics.org/](http://wateranalytics.org/)). This repository points to a community forum, and a bug reporting page that is actively monitored by a community of people that are looking to improve and expand EPANET.

_Why is git so complicated?_

Git is a distributed version control system that EPA has adopted for source code and software configuration management. It is powerful, but new users can find it complicated. Many online resources are available to help learn effective git usage. A great resource for learning Git is the GitHub help pages ( [https://help.github.com/](https://help.github.com/)).

_Is there a peer review process for contributions?_

Peer review is required for pull requests and is an important element of EPA project&#39;s quality control strategy. EPA has found through experience that peer review of contributions can be stressful for some contributing developers. EPA strives to maintain a professional peer review process and enforce a code of conduct within the development community to head off problems.

_What about quality assurance and documentation?_

Developed and maintained by EPA, EPANET is a commercial quality software. Rigorous quality assurance/quality control (QA/QC) and full documentation are hallmarks of commercial quality software. Therefore, QA/QC, testing, and documentation are essential aspects of the contributor process for EPANET. Contributors are expected to demonstrate the quality of their contribution and fully document in order for the contribution to be included in an official EPANET release. Software development is a process, development, testing, and documentation can occur in parallel over time while the maintainer works with the contributor on their contribution. When the contribution is accepted and ready (i.e., fully tested and documented), it is eligible to be scheduled for inclusion in an upcoming EPANET release.

_Why isn&#39;t my contribution being accepted?_

EPA is interested in open source development and community contributions to EPANET, but it is important to realize that contributions will not be automatically accepted. The EPA project officer reserves the final right to reject contributions from the official versions of EPANET. EPA will adhere to criteria of acceptance guidelines and be transparent in the decision-making process.

**Contact Information**

If you have any additional questions, please contact [epanet@epa.gov](mailto:epanet@epa.gov).