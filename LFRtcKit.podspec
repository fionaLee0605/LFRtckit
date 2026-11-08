#
# Be sure to run `pod lib lint LFRtcKit.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'LFRtcKit'
  s.version          = '0.1.1'
  s.summary          = 'RtcKit of LiveFuller'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/kerwin1232/LFRtckit'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'kerwin' => 'kerwin1232@163.com' }
  s.source           = { :git => 'https://github.com/kerwin1232/LFRtckit.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'
  s.swift_version = '5.0'
  s.vendored_frameworks = 'LFRtcKit/Classes/LiveFullerDC.framework'

  # Only compile our Swift patch files; the binary framework's headers stay vendored.
  s.source_files = 'LFRtcKit/Classes/**/*.{swift}'
  # s.resource_bundles = {
  #   'LFRtcKit' => ['LFRtcKit/Assets/*.png']
  # }
  s.pod_target_xcconfig = { 'VALID_ARCHS' => 'x86_64 arm64 armv7 armv7s' }
  # s.public_header_files = 'Pod/Classes/Header/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  s.dependency 'AgoraRtcEngine_iOS', '~> 3.6.1'
  s.dependency 'AgoraRtm_iOS','~> 1.4.8'
end
