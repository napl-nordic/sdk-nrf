.. _software_maturity:

Software maturity levels
########################

.. contents::
   :local:
   :depth: 2

The |NCS| supports its various features and components at different levels of software maturity.
The tables at the end of this page summarize the maturity level for each feature and component supported in the |NCS|.
The following categories are used in the tables to classify the software maturity of each feature and component:

Supported
   The feature or component is implemented and maintained, and is suitable for product development.

Not supported
   The feature or component is neither implemented nor maintained, and it does not work.

Experimental
   The feature can be used for development, but it is not recommended for production.
   This means that the feature is incomplete in functionality or verification and can be expected to change in future releases.
   The feature is made available in its current state, but the design and interfaces can change between release tags.
   The feature is also labeled as ``EXPERIMENTAL`` in Kconfig files to indicate this status.

   .. note::
      By default, the build system generates build warnings to indicate when features labeled ``EXPERIMENTAL`` are included in builds.
      To disable these warnings, disable the :kconfig:option:`CONFIG_WARN_EXPERIMENTAL` Kconfig option.
      See :ref:`app_build_additions` for details.

See the following table for more details:

.. _software_maturity_table:

.. list-table:: Software maturity
   :header-rows: 1
   :align: center
   :widths: auto

   * -
     - Supported
     - Experimental
     - Not supported
   * - **Technical support**
     - Customer issues raised for features supported for developing end products on tagged |NCS| releases are handled by technical support on DevZone.
     - Customer issues raised for experimental features on tagged |NCS| releases are handled by technical support on DevZone.
     - Not available.
   * - **Bug fixing**
     - Reported critical bugs and security fixes will be resolved in both ``main`` and the latest tagged versions.
     - Bug fixes, security fixes, and improvements are not guaranteed to be applied.
     - Not available.
   * - **Implementation completeness**
     - Complete implementation of the agreed features set.
     - Significant changes may be applied in upcoming versions.
     - A feature or component is available as an implementation, but is not compatible with (or tested on) a specific device or series of products.
   * - **API definition**
     - The API definition is stable.
     - The API definition is not stable and may change.
     - Not available.
   * - **Maturity**
     - Suitable for integration in end products.

       A feature or component that is either fully complete on first commit, or has previously been labelled *experimental* and is now ready for use in end products.

     - Suitable for prototyping or evaluation.
       Not recommended to be deployed in end products.

       A feature or component that is either not fully verified according to the existing test plans or currently being developed, meaning that it is incomplete or that it may change in the future.
     - Not applicable.

   * - **Verification**
     - Fully verified according to the existing test plans.
     - Incomplete verification
     - Not applicable.

.. _software_maturity_application:

Application support
*******************

The following subsections indicate the software maturity levels of the support for :ref:`applications <applications>`.

.. note::
    Features not listed are not supported.

.. _software_maturity_application_nrf5340audio:

nRF5340 Audio
=============

The following table indicates the software maturity levels of the support for the :ref:`nrf53_audio_app` application.

.. _software_maturity_application_nrf5340audio_table:

.. toggle::

   .. list-table:: nRF5340 Audio application feature support
      :header-rows: 1
      :align: center
      :widths: auto

      * - Feature
        - Description
        - Limitations
        - Maturity level
      * - **Broadcast source**
        - Transmitting broadcast audio using Broadcast Isochronous Stream (BIS) and Broadcast Isochronous Group (BIG).

          Play and pause emulated by disabling and enabling stream, respectively.
        - The following limitations apply:

          * Basic Audio Profile (BAP) broadcast, one BIG with two BIS streams.
          * Audio input: USB or I2S (Line in or using Pulse Density Modulation).
          * Configuration: 48 kHz, 16 bit, several bit rates ranging from 24 kbps to 160 kbps.

        - Experimental
      * - **Broadcast sink**
        - Receiving broadcast audio using BIS and BIG.

          Synchronizes and unsynchronizes with the stream.
        - The following limitations apply:

          * BAP broadcast, one BIG, one of the two BIS streams (selectable).
          * Audio output: I2S/Analog headset output.
          * Configuration: 48 kHz, 16 bit, several bit rates ranging from 24 kbps to 160 kbps.

        - Experimental
      * - **Unicast client**
        - BAP unicast, one Connected Isochronous Group (CIG) with two Connected Isochronous Streams (CIS).

          Transmitting unidirectional or transceiving bidirectional audio using CIG and CIS.

          Play and pause emulated by disabling and enabling stream, respectively.
        - The following limitations apply:

          * BAP unicast, one CIG with two CIS.
          * Bidirectional mode only supports connecting to *one* unicast server.
          * Audio input: USB or I2S (Line in or using Pulse Density Modulation).
          * Audio output: USB or I2S/Analog headset output.
          * Configuration: 48 kHz, 16 bit, several bit rates ranging from 24 kbps to 160 kbps.

        - Experimental
      * - **Unicast server**
        - BAP unicast, 1 CIG with 2 CIS streams.

          Receiving unidirectional or transceiving bidirectional audio using CIG and CIS.

          To emulate play and pause, the available context type for media is added or removed. This enables and disables streaming, respectively.
        - The following limitations apply:

          * BAP unicast, one CIG, one of the two CIS streams (selectable).
          * Audio output: I2S/Analog headset output.
          * Audio input: PDM microphone over I2S.
          * Configuration: 48 kHz, 16 bit, several bit rates ranging from 24 kbps to 160 kbps.

        - Experimental

.. _software_maturity_protocol:

Protocol support
****************

The following table indicates the software maturity levels of the support for each :ref:`protocol <protocols>`:

.. sml-table:: top_level

HomeKit features support
************************

The following table indicates the software maturity levels of the support for each HomeKit feature:

.. toggle::

  .. sml-table:: homekit

Thread features support
***********************

The following table indicates the software maturity levels of the support for each Thread feature:

.. toggle::

  .. sml-table:: thread

Matter features support
***********************

The following table indicates the software maturity levels of the support for each Matter feature:

.. toggle::

  .. sml-table:: matter

Zigbee feature support
**********************

The following table indicates the software maturity levels of the support for each Zigbee feature:

.. toggle::

  .. sml-table:: zigbee

Security Feature Support
************************

The following sections contain the tables indicating the software maturity levels of the support for the following security features:

* Trusted Firmware-M
* PSA Crypto
* |NSIB|
* Hardware Unique Key

Trusted Firmware-M support
==========================

.. toggle::

  .. sml-table:: trusted_firmware_m

PSA Crypto support
==================

.. toggle::

  .. sml-table:: psa_crypto

|NSIB|
======

.. toggle::

  .. sml-table:: immutable_bootloader

Hardware Unique Key
===================

.. toggle::

  .. sml-table:: hw_unique_key
