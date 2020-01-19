/*
 * This software is Copyright (C) 2006-2011
 * Fachhochschule Hannover (University of Applied Sciences and Arts)
 * Use is subject to license conditions.
 *
 * The main licensing options available are:
 *
 * Open Source Licensing. This is the appropriate option if you want to
 * share the source code of your application with everyone you
 * distribute it to, and you also want to give them the right to share
 * who uses it. If you wish to use TNC@FHH under Open Source Licensing,
 * you must contribute all your source code to the open source
 * community in accordance with the GPL Version 2 when your application
 * is distributed. See http://www.gnu.org/licenses/gpl-2.0.html/ or gpl-2.0.txt
 *
 * Commercial Licensing. This is the appropriate option if you are
 * creating proprietary applications and you are not prepared to
 * distribute and share the source code of your application.
 * Contact trust@f4-i.fh-hannover.de for details.
 *
 * http://trust.inform.fh-hannover.de/
 */

#ifndef XACMLCONSTANTS_H_
#define XACMLCONSTANTS_H_

#include <string>

namespace tncfhh {

namespace iml {

class XACMLConstants {

	public:
	/**
	 *
	 */
	static const std::string attribute_id_subject_id;
	static const std::string attribute_id_component_vendor_id;
	static const std::string attribute_id_component_type;
	static const std::string attribute_id_component_subtype;
	static const std::string attribute_id_attribute_vendor_id;
	static const std::string attribute_id_attribute_type;
	static const std::string attribute_id_product_information_vendor_id;
	static const std::string attribute_id_product_information_product_id;
	static const std::string attribute_id_product_information_product_name;
	static const std::string attribute_id_operational_status_status;
	static const std::string attribute_id_operational_status_result;
	static const std::string attribute_id_operational_status_last_use;
	static const std::string attribute_id_resource_id;
	static const std::string attribute_id_action_id;
	static const std::string attribute_id_attribute_numeric_version_major_version;
	static const std::string attribute_id_attribute_numeric_version_minor_version;
	static const std::string attribute_id_attribute_numeric_version_build_number;
	static const std::string attribute_id_attribute_numeric_version_service_pack_major;
	static const std::string attribute_id_attribute_numeric_version_service_pack_minor;
	static const std::string attribute_id_attribute_string_version_product_version_number;
	static const std::string attribute_id_attribute_string_version_internal_build_number;
	static const std::string attribute_id_attribute_string_version_configuration_version_number;
	static const std::string attribute_id_attribute_installed_packages_packages;
	static const std::string attribute_id_tncs_server_name;
	static const std::string attribute_id_component_recommendation_prefix;
	static const std::string attribute_id_component_recommendation_postfix;

	/**
	 *
	 */
	static const std::string data_type_rfc822_name;
	static const std::string data_type_xml_string;
	static const std::string data_type_xml_date_time;
	static const std::string data_type_xml_integer;

	/**
	 *
	 */
	static const std::string subject_category_tnc_ifm_component;
	static const std::string subject_category_tnc_ifm_attribute_product_information;
	static const std::string subject_category_tnc_ifm_attribute_operational_status;
	static const std::string subject_category_tnc_ifm_attribute_numeric_version;
	static const std::string subject_category_tnc_ifm_attribute_string_version;
	static const std::string subject_category_tnc_ifm_attribute_installed_packages;
	static const std::string subject_category_tnc_tncs;
};

}// namespace iml

} // namespace tncfhh

#endif /* XACMLCONSTANTS_H_ */
